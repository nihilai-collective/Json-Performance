
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2480 | 0.0402045 | 4909.31ms | 108313 | 4890 | 1.37124e+06 | 41651.3 | 0.00319742 | 2.04188 | 8.69621 | 1.76492 | 0.00293055 | 2.26848e-05 | 1.26725e-05 | 1(Win) | true |
| Glaze | 2286.17 | 0.0766188 | 5256.61ms | 108313 | 4890 | 5.86034e+06 | 45182.6 | 0.109697 | 2.21422 | 10.5617 | 1.88794 | 0.00279159 | 3.13188e-05 | 1.9039e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1934.15 | 0.198934 | 6058.45ms | 108313 | 160 | 1.806e+06 | 53406 | 0.00737223 | 2.61436 | 12.0538 | 2.14476 | 0.00299733 | 1.96191e-05 | 1.09059e-05 | 3(Loss) | true |
| simdjson (ondemand) | 715.638 | 0.0549515 | 7764.23ms | 108313 | 2560 | 1.61055e+07 | 144340 | 0.107351 | 7.04649 | 30.9486 | 4.41788 | 0.00408001 | 0.000104396 | 6.7354e-05 | 4(Loss) | true |
