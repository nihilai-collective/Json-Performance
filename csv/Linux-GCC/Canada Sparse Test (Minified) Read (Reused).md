
----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8525.08 | 0.140999 | 6295.57ms | 2090234 | 40 | 4.34796e+06 | 233828 | 0.271715 | 0.59217 | 3.18958 | 0.396895 | 0.00244135 | 0.0501908 | 3.97085e-06 | 1(Win) | true |
| simdjson (ondemand) | 7254.83 | 0.228664 | 7290.41ms | 2090234 | 80 | 3.15807e+07 | 274769 | 0.261025 | 0.706786 | 3.6662 | 0.418386 | 0.00235827 | 0.0497088 | 5.74098e-07 | 2(Loss) | true |
