
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1391.66 | 0.493974 | 113.757ms | 1691 | 4890 | 160228 | 1158.81 | 0.40774 | 1(Win) | true |
| Glaze | 1365.68 | 0.520076 | 122.064ms | 1691 | 4890 | 184429 | 1180.85 | 0.258601 | 2(Loss) | true |
| simdjson (ondemand) | 1127.82 | 0.705243 | 145.785ms | 1691 | 2560 | 260332 | 1429.9 | 0.527278 | 3(Loss) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1101.47 | 0.770324 | 148.647ms | 1691 | 2560 | 325633 | 1464.1 | 2.04068 | 4(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1085.53 | 1.41389 | 158.513ms | 1691 | 640 | 282368 | 1485.6 | 1.11821 | 4(Tie) | true |
