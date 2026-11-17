
----
### Twitter Partial Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 3557.99 | 0.200563 | 80.4701ms | 2889 | 320 | 771.855 | 774.359 | 0.0181635 | 1(Win) | true |
| simdjson (ondemand) | 3420.16 | 0.453816 | 88.8623ms | 2889 | 30 | 400.944 | 805.567 | 0.686283 | 2(Loss) | true |
| Jsonifier | 2984.16 | 0.604003 | 86.5612ms | 2889 | 4890 | 152069 | 923.264 | 1.05182 | 3(Loss) | true |
| Glaze | 1882.11 | 0.311524 | 145.763ms | 2889 | 2560 | 53238.5 | 1463.87 | 0.33341 | 4(Loss) | true |
