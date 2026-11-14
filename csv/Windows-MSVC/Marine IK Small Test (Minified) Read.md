
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 492.941 | 0.0700044 | 895.866ms | 4604 | 2560 | 99534.1 | 8907.19 | 0.0473859 | 6.15146 | 1(Win) | true |
| Jsonifier | 475.025 | 0.321048 | 933.447ms | 4604 | 640 | 563583 | 9243.12 | 0.118191 | 6.3846 | 2(Loss) | true |
| simdjson (ondemand) | 317.137 | 0.127975 | 1385.23ms | 4604 | 640 | 200912 | 13844.8 | 0.00112857 | 9.56901 | 3(Loss) | true |
| Glaze | 284.474 | 0.0658211 | 1550.76ms | 4604 | 4890 | 504690 | 15434.5 | 0.0871814 | 10.661 | 4(Loss) | true |
