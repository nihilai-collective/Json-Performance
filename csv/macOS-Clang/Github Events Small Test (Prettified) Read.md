
----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1208.18 | 0.095453 | 173.403ms | 2158 | 160 | 422.999 | 1703.41 | 0.106291 | 1(Win) | true |
| simdjson (ondemand) | 1044.66 | 0.0738539 | 204.118ms | 2158 | 320 | 677.411 | 1970.05 | 0.448318 | 2(Loss) | true |
