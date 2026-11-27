
----
### Discord Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 555.545 | 0.134814 | 835.966ms | 4857 | 4890 | 617840 | 8337.75 | 0.0245599 | 1(Win) | true |
| simdjson (ondemand) | 162.43 | 0.382404 | 2872.2ms | 4857 | 160 | 1.90268e+06 | 28516.8 | 0.196762 | 2(Loss) | true |
