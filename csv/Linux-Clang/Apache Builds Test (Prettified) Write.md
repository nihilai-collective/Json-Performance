
----
### Apache Builds Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 19040.6 | 0.0404838 | 1425.06ms | 136037 | 4890 | 37207.2 | 6813.61 | 0.00760588 | 0.266248 | 1.27855 | 0.214993 | 0.000175758 | 3.98214e-06 | 1.73627e-06 | 1(Win) | true |
| Glaze | 5312.8 | 0.0936838 | 3197.77ms | 136076 | 640 | 335139 | 24426.3 | 0.0577196 | 0.952023 | 4.09562 | 0.69046 | 0.00144909 | 1.14596e-05 | 3.8811e-06 | 2(Loss) | true |
