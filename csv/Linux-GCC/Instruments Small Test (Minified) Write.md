
----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12187.9 | 0.0585765 | 760.405ms | 4669 | 640 | 29.31 | 365.337 | 0.0555684 | 0.468333 | 1.25958 | 0.318269 | 0.000214513 | 2.14179e-05 | 5.01981e-06 | 1(Win) | true |
| simdjson (reflection) | 8326.32 | 0.164853 | 810.776ms | 4669 | 80 | 62.1766 | 534.775 | 0.0373849 | 0.665324 | 1.64575 | 0.218034 | 0.000214179 | 3.4804e-05 | 1.07089e-05 | 2(Loss) | true |
| Glaze | 3909.31 | 0.277974 | 840.639ms | 4669 | 4890 | 49019 | 1139 | 0.163269 | 1.36109 | 3.46932 | 0.501403 | 0.000217639 | 5.54499e-05 | 2.44838e-05 | 3(Loss) | true |
