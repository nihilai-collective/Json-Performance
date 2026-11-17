
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 944.573 | 0.512969 | 7745.43ms | 2090234 | 30 | 3.51579e+09 | 2.11038e+06 | 0.189973 | 5.41087 | 25.0602 | 4.35791 | 0.0224841 | 0.0806506 | 0.000639546 | 1(Win) | true |
| Jsonifier (generic) | 902.867 | 0.178674 | 8072.82ms | 2090234 | 80 | 1.24496e+09 | 2.20786e+06 | 0.129119 | 5.61663 | 25.6684 | 5.12899 | 0.0214033 | 0.079108 | 0.00153053 | 2(Loss) | true |
