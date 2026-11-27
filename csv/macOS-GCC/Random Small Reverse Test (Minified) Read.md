
----
### Random Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 601.588 | 0.273442 | 787.025ms | 4926 | 1280 | 583623 | 7809 | 0.476068 | 1(Win) | true |
| simdjson (ondemand) | 320.183 | 0.10019 | 1445.58ms | 4926 | 4890 | 1.0567e+06 | 14672.3 | 0.0459485 | 2(Loss) | true |
