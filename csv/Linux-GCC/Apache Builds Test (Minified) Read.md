
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1664.77 | 0.0361238 | 6223.11ms | 94653 | 1280 | 491084 | 54222.5 | 0.0538894 | 3.03008 | 13.8341 | 2.46038 | 0.00893498 | 2.46129e-05 | 1.74403e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1446.15 | 0.0509098 | 7032.2ms | 94653 | 640 | 646291 | 62419.8 | 0.0525473 | 3.50108 | 15.6443 | 2.74241 | 0.00958843 | 2.42663e-05 | 1.65242e-05 | 2(Loss) | true |
| simdjson (reflection) | 1408.22 | 0.0156777 | 7161.18ms | 94653 | 4890 | 493856 | 64100.7 | 0.0667013 | 3.57455 | 14.1504 | 2.60997 | 0.00812774 | 1.20449e-05 | 6.18987e-06 | 3(Loss) | true |
| Glaze | 1389.9 | 0.158949 | 7230.46ms | 94653 | 160 | 1.70505e+06 | 64945.8 | 0.00156864 | 3.63258 | 15.5413 | 3.09745 | 0.0155037 | 1.00367e-05 | 5.94276e-06 | 4(Loss) | true |
| simdjson (ondemand) | 1361.93 | 0.074081 | 7366.2ms | 94653 | 640 | 1.54296e+06 | 66279.6 | 0.0259786 | 3.69872 | 14.5333 | 2.90228 | 0.0109176 | 9.13204e-05 | 4.97376e-05 | 5(Loss) | true |
