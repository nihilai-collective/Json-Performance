
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3163.42 | 0.298871 | 349.582ms | 9578 | 80 | 5957.9 | 2887.47 | 0.964638 | 1(Win) | true |
| simdjson (stage-1) | 2934.78 | 0.204516 | 343.061ms | 9578 | 30 | 1215.56 | 3112.43 | 0.756763 | 2(Loss) | true |
