
----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1298.24 | 0.0750353 | 8552.75ms | 1834197 | 30 | 3.06645e+07 | 1.34739e+06 | 0.135889 | 3.88809 | 13.1333 | 0.799078 | 0.00231071 | 0.060403 | 0.000216734 | 1(Win) | true |
| Glaze | 981.979 | 0.200291 | 5530.73ms | 1833577 | 160 | 2.03534e+09 | 1.78073e+06 | 0.0186192 | 5.12822 | 16.0488 | 1.05286 | 0.000995677 | 0.049589 | 9.92629e-05 | 2(Loss) | true |
| simdjson (reflection) | 883.168 | 0.032504 | 6466.25ms | 1922245 | 40 | 1.82081e+07 | 2.0757e+06 | 0.0698122 | 5.71409 | 18.1523 | 2.01851 | 0.0263587 | 0.0502403 | 0.000219886 | 3(Loss) | true |
