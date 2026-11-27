
----
### Discord Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1976.32 | 0.155161 | 4229.47ms | 83958 | 320 | 1.26451e+06 | 40514 | 0.0287021 | 1(Win) | true |
| simdjson (ondemand) | 1616.43 | 0.112871 | 5054.04ms | 83958 | 1280 | 4.00113e+06 | 49534.1 | 0.0504779 | 2(Loss) | true |
