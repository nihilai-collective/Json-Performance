
----
### Uint64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2595.7 | 0.125844 | 53.5355ms | 1213 | 80 | 25.1631 | 445.663 | 0.00280489 | 0.895373 | 1(Win) | true |
| simdjson (reflection) | 2190.46 | 0.0468009 | 61.9842ms | 1213 | 320 | 19.5484 | 528.112 | 0.0722432 | 1.072 | 2(Loss) | true |
| Glaze | 1312.58 | 0.0585549 | 96.702ms | 1213 | 160 | 42.6107 | 881.325 | 0.0155991 | 1.82931 | 3(Loss) | true |
