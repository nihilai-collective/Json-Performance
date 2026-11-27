
----
### Discord Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2562.29 | 0.0732102 | 206.19ms | 4857 | 160 | 280.248 | 1807.76 | 0.0252321 | 0.951292 | 1(Win) | true |
| Glaze | 2009.17 | 0.142522 | 254.269ms | 4857 | 40 | 431.84 | 2305.43 | 0.0126529 | 1.21768 | 2(Loss) | true |
| Jsonifier (two-stage) | 1915.37 | 0.124488 | 263.934ms | 4857 | 40 | 362.533 | 2418.32 | 0.288964 | 1.27765 | 3(Loss) | true |
| simdjson (reflection) | 1796.65 | 0.109552 | 280.829ms | 4857 | 40 | 319.087 | 2578.12 | 0.190098 | 1.36341 | 4(Loss) | true |
| simdjson (ondemand) | 1578.36 | 0.0571172 | 320.688ms | 4857 | 80 | 224.775 | 2934.69 | 0.677311 | 1.55419 | 5(Loss) | true |
