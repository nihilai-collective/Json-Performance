
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 928.255 | 0.248502 | 8222.6ms | 2090234 | 160 | 4.55656e+09 | 2.14747e+06 | 0.499793 | 2.66713 | 1(Win) | true |
| simdjson (ondemand) | 853.911 | 0.80767 | 8891.15ms | 2090234 | 80 | 2.84395e+10 | 2.33444e+06 | 0.0434177 | 2.89934 | 2(Loss) | true |
