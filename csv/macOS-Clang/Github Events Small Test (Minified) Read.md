
----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1053.41 | 0.0596144 | 159.086ms | 1691 | 640 | 533.063 | 1530.9 | 0.0305264 | 1(Win) | true |
| simdjson (ondemand) | 828.045 | 0.105979 | 199.463ms | 1691 | 4890 | 20831.9 | 1947.56 | 0.0734877 | 2(Loss) | true |
