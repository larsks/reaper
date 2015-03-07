Reaper launches whatever command you specify on the command line and
then hangs around wait()ing for things to exit.  Useful inside a
Docker container to avoid zombie processes:

    CMD reaper myservice --my-options

