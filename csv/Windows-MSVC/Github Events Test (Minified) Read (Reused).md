
----
### Github Events Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1682.5 | 0.0650593 | 3704.41ms | 53331 | 2560 | 990167 | 30229.1 | 0.0661178 | 1.80473 | 1(Win) | true |
| Glaze | 1589.1 | 0.0512172 | 3853.04ms | 53331 | 4890 | 1.31401e+06 | 32005.8 | 0.298402 | 1.9111 | 2(Loss) | true |
| Jsonifier (two-stage) | 1433.25 | 0.0542693 | 4231.22ms | 53331 | 4890 | 1.81358e+06 | 35486.2 | 0.0116809 | 2.11916 | 3(Loss) | true |
| simdjson (ondemand) | 957.433 | 0.0757517 | 5889.91ms | 53331 | 1280 | 2.07271e+06 | 53121.6 | 0.247243 | 3.17298 | 4(Loss) | true |
