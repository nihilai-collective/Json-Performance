
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3205.58 | 0.0464021 | 3973.65ms | 108313 | 640 | 143088 | 32223.6 | 0.0277815 | 1.57824 | 7.40082 | 1.50827 | 0.0021865 | 2.10328e-05 | 1.49884e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 2236.67 | 0.0915003 | 5377.51ms | 108313 | 80 | 142854 | 46182.7 | 0.0450723 | 2.2598 | 10.3059 | 1.84188 | 0.0026802 | 9.34791e-06 | 6.46275e-06 | 2(Loss) | true |
| Glaze | 2223.56 | 0.0866913 | 5386.48ms | 108313 | 320 | 518995 | 46454.8 | 0.0481613 | 2.27373 | 10.0551 | 1.92674 | 0.00312301 | 1.53202e-05 | 9.14595e-06 | 3(Loss) | true |
| simdjson (reflection) | 1686.88 | 0.0436804 | 6887.49ms | 108313 | 320 | 228937 | 61234.6 | 0.0443011 | 2.99629 | 13.097 | 2.03448 | 0.00224139 | 6.48295e-05 | 5.10961e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1446.95 | 0.0454775 | 7900.57ms | 108313 | 4890 | 5.15413e+06 | 71388.3 | 0.0234845 | 3.48509 | 14.907 | 2.64241 | 0.00276354 | 3.12602e-05 | 2.03549e-05 | 5(Loss) | true |
