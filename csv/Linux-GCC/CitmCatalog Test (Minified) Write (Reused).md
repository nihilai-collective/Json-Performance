
----
### CitmCatalog Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12472.8 | 0.0861594 | 4596.29ms | 500299 | 160 | 173802 | 38252.9 | 0.0150175 | 0.405379 | 1.81463 | 0.301572 | 0.00142219 | 0.0050575 | 2.41106e-06 | 1(Win) | true |
| simdjson (reflection) | 11161.5 | 0.0268177 | 5067.75ms | 500299 | 1280 | 168216 | 42747.2 | 0.0448476 | 0.452956 | 2.18004 | 0.196834 | 0.00137188 | 0.000946743 | 6.74284e-06 | 2(Loss) | true |
| Glaze | 7203.28 | 0.0516034 | 7361.35ms | 500299 | 640 | 747713 | 66236.8 | 0.00462614 | 0.696838 | 3.75128 | 0.547385 | 0.00156164 | 0.000196354 | 6.062e-06 | 3(Loss) | true |
