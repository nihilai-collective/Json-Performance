
----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 10910.1 | 0.0713488 | 28.5955ms | 2963 | 1280 | 43.7107 | 259.002 | 0.0633844 | 0.204166 | 1(Win) | true |
| simdjson (reflection) | 9964.36 | 0.122533 | 31.9933ms | 2963 | 320 | 38.6386 | 283.584 | 0.477068 | 0.225804 | 2(Loss) | true |
| Glaze | 5166.53 | 0.138142 | 57.572ms | 2963 | 160 | 91.3349 | 546.931 | 0.00571402 | 0.456946 | 3(Loss) | true |
