
----
### Github Events Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1045.48 | 0.0243772 | 6240.04ms | 65103 | 40 | 8383.02 | 59386.4 | 0.34904 | 1(Win) | true |
| simdjson (ondemand) | 419.26 | 0.1142 | 7604.14ms | 65103 | 640 | 1.8304e+07 | 148087 | 0.0851086 | 2(Loss) | true |
