
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11808.7 | 0.0986706 | 846.604ms | 9578 | 4890 | 2848.58 | 773.52 | 0.248578 | 0.452113 | 1.88557 | 0.21539 | 0.00063805 | 2.29522e-05 | 1.00563e-05 | 1(Win) | true |
| Glaze | 4535.17 | 0.280785 | 965.327ms | 9578 | 30 | 959.472 | 2014.1 | 0.137176 | 1.13885 | 4.99374 | 0.731781 | 0.000539431 | 6.61238e-05 | 6.9604e-06 | 2(Loss) | true |
