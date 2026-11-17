
----
### Apache Builds Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20553.2 | 0.0547578 | 1178.17ms | 94653 | 640 | 3701.54 | 4391.93 | 0.0276354 | 0.248564 | 1.19515 | 0.179403 | 4.07739e-05 | 2.06346e-06 | 3.30153e-07 | 1(Win) | true |
| simdjson (reflection) | 13488.4 | 0.0326479 | 1404.13ms | 94653 | 2560 | 12220.7 | 6692.26 | 0.0178118 | 0.376903 | 2.03945 | 0.301639 | 3.21899e-05 | 3.59454e-06 | 1.57648e-06 | 2(Loss) | true |
| Glaze | 9303.76 | 0.0433314 | 1712.39ms | 94653 | 1280 | 22623.9 | 9702.33 | 0.126313 | 0.543198 | 3.41879 | 0.557426 | 5.30804e-05 | 2.3771e-06 | 7.92368e-07 | 3(Loss) | true |
