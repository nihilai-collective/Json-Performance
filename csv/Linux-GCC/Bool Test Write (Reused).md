
----
### Bool Test Write (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3080.49 | 0.238365 | 35.9921ms | 905 | 40 | 17.8404 | 280.175 | 0.210733 | 0.727459 | 1(Win) | true |
| simdjson (reflection) | 2431.41 | 0.0795994 | 44.6736ms | 905 | 320 | 25.5476 | 354.969 | 0.119872 | 0.941105 | 2(Loss) | true |
| Glaze | 1063.47 | 0.21043 | 89.109ms | 905 | 30 | 87.4954 | 811.567 | 0.0369519 | 2.25227 | 3(Loss) | true |
