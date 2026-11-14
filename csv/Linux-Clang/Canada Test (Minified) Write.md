
----
### Canada Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1938.6 | 0.0410698 | 6543.11ms | 2090234 | 320 | 5.707e+07 | 1.02827e+06 | 0.145422 | 2.60063 | 7.89149 | 0.405686 | 0.000237699 | 0.051073 | 7.01447e-05 | 1(Win) | true |
| Glaze | 958.459 | 0.0766799 | 6487.84ms | 2090234 | 160 | 4.06936e+08 | 2.0798e+06 | 0.155352 | 5.22798 | 9.3422 | 0.534101 | 0.000241277 | 0.0694802 | 0.00185313 | 2(Loss) | true |
