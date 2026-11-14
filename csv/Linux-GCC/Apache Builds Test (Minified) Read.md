
----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14369.2 | 0.113029 | 1339.14ms | 94653 | 40 | 2016.74 | 6282.07 | 0.16862 | 0.354312 | 1.71452 | 0.0716301 | 2.13939e-05 | 1.98092e-05 | 1.10932e-05 | 1(Win) | true |
| simdjson (stage-1) | 13466.4 | 0.04269 | 1388.86ms | 94653 | 40 | 327.549 | 6703.2 | 0.0034808 | 0.38493 | 2.00727 | 0.0771027 | 1.98092e-05 | 3.43359e-06 | 0 | 2(Loss) | true |
