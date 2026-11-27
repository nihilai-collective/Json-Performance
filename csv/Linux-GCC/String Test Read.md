
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1377.11 | 0.083338 | 1012.96ms | 4215 | 640 | 3787.23 | 2918.96 | 0.116562 | 3.79078 | 17.4771 | 3.1331 | 0.000465599 | 4.67082e-05 | 1.29745e-05 | 1(Win) | true |
| Glaze | 1002.06 | 0.049956 | 1123ms | 4215 | 2560 | 10280.7 | 4011.48 | 0.103123 | 5.15401 | 23.5224 | 4.66857 | 0.00145509 | 7.33986e-05 | 7.7847e-06 | 2(Loss) | true |
| simdjson (reflection) | 972.276 | 0.0313669 | 1138.98ms | 4215 | 4890 | 8223.73 | 4134.36 | 0.227851 | 5.26807 | 21.5898 | 4.52883 | 0.00158752 | 7.5929e-05 | 3.06627e-05 | 3(Loss) | true |
| simdjson (ondemand) | 917.763 | 0.0393831 | 1160.64ms | 4215 | 4890 | 14550 | 4379.93 | 0.0357606 | 5.63595 | 25.7144 | 4.23772 | 0.00258338 | 6.03551e-05 | 1.63017e-05 | 4(Loss) | true |
