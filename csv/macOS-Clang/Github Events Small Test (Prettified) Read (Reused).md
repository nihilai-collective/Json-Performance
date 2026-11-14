
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1314.03 | 0.423801 | 178.79ms | 2158 | 2560 | 112787 | 1566.2 | 0.412572 | 1(Win) | true |
| simdjson (ondemand) | 1129.78 | 0.150618 | 204.557ms | 2158 | 160 | 1204.44 | 1821.61 | 0.0714163 | 2(Loss) | true |
