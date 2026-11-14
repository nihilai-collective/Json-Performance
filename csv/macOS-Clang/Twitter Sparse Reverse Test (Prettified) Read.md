
----
### Twitter Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3503.03 | 0.123083 | 5095.86ms | 360584 | 640 | 9.34329e+06 | 98166.5 | 0.111604 | 1(Win) | true |
| simdjson (ondemand) | 2858.46 | 0.17042 | 6214.64ms | 360584 | 640 | 2.69012e+07 | 120302 | 0.029965 | 2(Loss) | true |
