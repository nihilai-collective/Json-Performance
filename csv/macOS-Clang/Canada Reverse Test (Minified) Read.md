
----
### Canada Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 498.936 | 0.10706 | 6133.77ms | 2090234 | 80 | 1.46366e+09 | 3.99531e+06 | 0.00309028 | 1(Win) | true |
| simdjson (ondemand) | 454.046 | 0.155966 | 6663.53ms | 2090234 | 30 | 1.40661e+09 | 4.39031e+06 | 0.168586 | 2(Loss) | true |
