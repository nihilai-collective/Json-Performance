
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6888.9 | 0.625233 | 6642.67ms | 466906 | 80 | 1.30657e+07 | 64636.8 | 0.251852 | 1(Win) | true |
| simdjson (stage-1) | 5975.47 | 0.225124 | 7224.36ms | 466906 | 4890 | 1.37615e+08 | 74517.4 | 0.436442 | 2(Loss) | true |
