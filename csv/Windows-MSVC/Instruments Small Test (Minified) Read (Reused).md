
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1558.25 | 0.277019 | 307.191ms | 4669 | 40 | 2506.41 | 2857.5 | 0.0874126 | 1.57522 | 1(Win) | true |
| Jsonifier (two-stage) | 1107.64 | 0.184771 | 422.519ms | 4669 | 30 | 1655.17 | 4020 | 0.08285 | 2.22689 | 2(Loss) | true |
| Glaze | 987.844 | 0.146203 | 480.596ms | 4669 | 40 | 1737.18 | 4507.5 | 0.202952 | 2.49029 | 3(Loss) | true |
| simdjson (ondemand) | 658.197 | 0.0559145 | 714.231ms | 4669 | 160 | 2289.31 | 6765 | 0.0554017 | 3.74633 | 4(Loss) | true |
