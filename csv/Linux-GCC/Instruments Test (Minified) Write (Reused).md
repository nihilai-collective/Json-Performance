
----
### Instruments Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20205.4 | 0.036812 | 1251.47ms | 108313 | 4890 | 17318.6 | 5112.26 | 0.0764159 | 0.251804 | 1.08875 | 0.287694 | 0.000109548 | 3.99886e-06 | 1.88804e-06 | 1(Win) | true |
| simdjson (reflection) | 15550.3 | 0.0779856 | 1405.35ms | 108313 | 640 | 17174.9 | 6642.67 | 0.042181 | 0.326944 | 1.48913 | 0.192645 | 0.000183424 | 6.11653e-06 | 3.07269e-06 | 2(Loss) | true |
| Glaze | 6414.25 | 0.0642784 | 2353.74ms | 108313 | 4890 | 523972 | 16104 | 0.0938397 | 0.788176 | 2.97166 | 0.386768 | 0.00028319 | 5.89068e-06 | 3.00764e-06 | 3(Loss) | true |
