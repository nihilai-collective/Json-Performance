
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 659.711 | 0.103987 | 132.203ms | 905 | 4890 | 9050.16 | 1308.26 | 0.0313641 | 4.54298 | 1(Win) | true |
| Glaze | 632.869 | 0.396594 | 139.709ms | 905 | 80 | 2340.19 | 1363.75 | 1.01852 | 4.7324 | 2(Loss) | true |
| Jsonifier (two-stage) | 264.601 | 0.200015 | 329.531ms | 905 | 1280 | 54481.5 | 3261.8 | 0.0407342 | 11.4206 | 3(Loss) | true |
| simdjson (ondemand) | 121.458 | 0.174851 | 711.762ms | 905 | 320 | 49400.4 | 7105.94 | 0.0483516 | 24.9701 | 4(Loss) | true |
