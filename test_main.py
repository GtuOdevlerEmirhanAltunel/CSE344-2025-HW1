"""This file contains the tests for the main file."""

import subprocess
import os
import pytest


def compile_project():
    """Compile the project."""
    print("Compiling...")
    ret = subprocess.run(["make"], check=True)
    if ret.returncode != 0:
        raise RuntimeError("Failed to compile the project.")


def clean_project():
    """Clean the project."""
    print("Cleaning...")
    subprocess.run(["make", "fclean"], check=True)


@pytest.fixture(scope="function", autouse=True)
def setup_and_teardown():
    """Setup and teardown the tests."""
    compile_project()
    yield
    clean_project()


def run_command(
    command: list[str], expected_output: str, expected_returncode: int
):
    """Run a command."""
    print(f"Running command: {command}")
    ret = subprocess.run(
        ["./main.out", *command], check=False, capture_output=True
    )
    assert ret.returncode == expected_returncode
    assert ret.stdout.decode("utf-8")[20:].strip() == expected_output
    with open("log.txt", "r", encoding="utf-8") as file:
        file_content = file.read()
    assert file_content[20:].strip() == expected_output


argument_count = {"createDir": 1, "createFile": 1}


@pytest.mark.parametrize("command", argument_count.keys())
def test_command_less_argument_count(command):
    """Test the command with less arguments than required."""
    if argument_count[command] > 0:
        run_command(
            [command, *["arg1"] * (argument_count[command] - 1)],
            f"Command {command} requires {argument_count[command]} "
            + f"arguments, {argument_count[command] - 1} provided",
            1,
        )


@pytest.mark.parametrize("command", argument_count.keys())
def test_command_more_argument_count(command):
    """Test the command with more arguments than required."""
    run_command(
        [command, *["arg1"] * (argument_count[command] + 1)],
        f"Command {command} requires {argument_count[command]} "
        + f"arguments, {argument_count[command] + 1} provided",
        1,
    )


def test_create_dir_with_success():
    """Test the createDir command."""
    run_command(
        ["createDir", "test_folder"], "Directory test_folder created", 0
    )


def test_create_dir_with_existing_dir():
    """Test the createDir command."""
    os.mkdir("test_folder")
    run_command(
        ["createDir", "test_folder"],
        "File/Folder test_folder already exists, cannot create.",
        1,
    )


def test_create_dir_with_existing_file():
    """Test the createDir command."""
    with open("test_folder", "w", encoding="utf-8") as file:
        file.write("test")
    run_command(
        ["createDir", "test_folder"],
        "File/Folder test_folder already exists, cannot create.",
        1,
    )


def test_create_file_with_success():
    """Test the createFile command."""
    run_command(["createFile", "test_file"], "File test_file created", 0)


def test_create_file_with_existing_dir():
    """Test the createFile command."""
    os.mkdir("test_file")
    run_command(
        ["createFile", "test_file"],
        "File/Folder test_file already exists, cannot create.",
        1,
    )


def test_create_file_with_existing_file():
    """Test the createFile command."""
    with open("test_file", "w", encoding="utf-8") as file:
        file.write("test")
    run_command(
        ["createFile", "test_file"],
        "File/Folder test_file already exists, cannot create.",
        1,
    )
