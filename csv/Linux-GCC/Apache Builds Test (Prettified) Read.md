
----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14475.3 | 0.038608 | 1547.54ms | 124597 | 2560 | 25713.1 | 8208.81 | 0.06717 | 0.355476 | 1.71319 | 0.0635249 | 1.64969e-05 | 2.1256e-06 | 9.37397e-07 | 1(Win) | true |
| simdjson (stage-1) | 14091.8 | 0.0287432 | 1558.97ms | 124597 | 160 | 939.88 | 8432.19 | 0.0275063 | 0.36753 | 1.83555 | 0.0691991 | 2.02152e-05 | 1.45469e-06 | 5.01617e-08 | 2(Loss) | true |
