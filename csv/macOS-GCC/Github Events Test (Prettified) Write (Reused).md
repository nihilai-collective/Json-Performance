
----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15377.5 | 0.510742 | 496.079ms | 78778 | 640 | 398492 | 4885.6 | 1.46204 | 1(Win) | true |
| Glaze | 3979.27 | 0.540086 | 2105.63ms | 78778 | 40 | 415902 | 18880 | 0.292925 | 2(Loss) | true |
| simdjson (reflection) DID NOT CONVERGE | 397.401 | 0.587369 | 9736.73ms | 78778 | 80 | 9.86424e+07 | 189050 | 5.04677 | -(Loss) | false |
