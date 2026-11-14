
----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5081.9 | 1.05034 | 8031.35ms | 6661897 | 40 | 6.89708e+09 | 1.25018e+06 | 0.38521 | 0.991145 | 2.92469 | 0.261234 | 7.4746e-05 | 0.0280316 | 0.000176076 | 1(Win) | true |
| Glaze | 3912.79 | 0.673024 | 5124.39ms | 6661897 | 40 | 4.77688e+09 | 1.62372e+06 | 0.154292 | 1.29378 | 4.22891 | 0.468988 | 8.43453e-05 | 0.0244618 | 0.000223634 | 2(Loss) | true |
