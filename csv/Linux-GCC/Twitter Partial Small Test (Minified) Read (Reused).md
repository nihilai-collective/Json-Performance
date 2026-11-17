
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7120.47 | 0.0393332 | 63.9229ms | 2889 | 1280 | 29.6487 | 386.936 | 0.0327196 | 0.324405 | 1(Win) | true |
| simdjson (reflection) | 6471.13 | 0.131944 | 45.2252ms | 2889 | 80 | 25.2467 | 425.762 | 0.0850689 | 0.358056 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 6141.93 | 0.0846565 | 47.4429ms | 2889 | 640 | 92.2967 | 448.583 | 0.17351 | 0.378543 | 3(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6131.64 | 0.0792684 | 48.098ms | 2889 | 640 | 81.1937 | 449.336 | 0.283986 | 0.379779 | 3(Tie) | true |
| Glaze | 3036.44 | 0.143499 | 92.7546ms | 2889 | 30 | 50.8609 | 907.367 | 0.554098 | 0.792223 | 5(Loss) | true |
