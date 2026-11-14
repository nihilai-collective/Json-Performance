
----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 839.091 | 0.643608 | 8574.2ms | 2090234 | 80 | 1.87027e+10 | 2.37567e+06 | 0.408588 | 6.07703 | 29.3791 | 5.31764 | 0.0222059 | 0.154876 | 0.00114921 | 1(Win) | true |
| Jsonifier (generic) | 794.767 | 0.715448 | 8939.86ms | 2090234 | 80 | 2.57606e+10 | 2.50816e+06 | 0.325872 | 6.44239 | 28.6896 | 5.7597 | 0.020972 | 0.130261 | 0.000832807 | 2(Loss) | true |
