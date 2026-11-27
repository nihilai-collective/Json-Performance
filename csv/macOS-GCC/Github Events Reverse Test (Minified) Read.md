
----
### Github Events Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 875.021 | 0.259648 | 5852.08ms | 53331 | 160 | 3.6443e+06 | 58124.8 | 0 | 1(Win) | true |
| simdjson (ondemand) | 448.087 | 0.115307 | 6052ms | 53331 | 320 | 5.4815e+06 | 113506 | 0.236257 | 2(Loss) | true |
