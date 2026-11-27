
----
### CitmCatalog Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2562.6 | 0.0516321 | 9922.75ms | 500299 | 640 | 5.91449e+06 | 186187 | 0.000824938 | 1.98335 | 9.65309 | 1.69343 | 0.00755361 | 0.00115139 | 4.97921e-05 | 1(Win) | true |
| Glaze | 1985.98 | 0.100559 | 6358.8ms | 500299 | 160 | 9.3384e+06 | 240245 | 0.0816475 | 2.58581 | 11.5064 | 2.23425 | 0.010149 | 0.000420723 | 4.07881e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1924.41 | 0.0689864 | 6560.55ms | 500299 | 320 | 9.36143e+06 | 247932 | 0.160563 | 2.64936 | 12.5476 | 2.15832 | 0.0109177 | 0.0147633 | 0.000117523 | 3(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1546.03 | 0.0455203 | 8080.54ms | 500299 | 640 | 1.26303e+07 | 308612 | 0.112287 | 3.30484 | 13.703 | 2.37513 | 0.01542 | 0.0140077 | 0.000228417 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1543.34 | 0.0977383 | 8149.37ms | 500299 | 160 | 1.46078e+07 | 309149 | 0.0857789 | 3.32367 | 14.0855 | 2.42378 | 0.0137424 | 0.0144597 | 0.000182866 | 4(Tie) | true |
