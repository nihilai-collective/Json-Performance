
----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11771.2 | 0.0738524 | 759.349ms | 4857 | 4890 | 412.981 | 393.501 | 0.288226 | 0.480046 | 1.59069 | 0.225448 | 0.000206015 | 2.03783e-05 | 7.57871e-06 | 1(Win) | true |
| simdjson (reflection) | 9260.29 | 0.132958 | 770.492ms | 4857 | 30 | 13.269 | 500.2 | 0.0998602 | 0.612552 | 1.93515 | 0.296685 | 0.000281381 | 2.74518e-05 | 0 | 2(Loss) | true |
| Glaze | 4931.82 | 0.399079 | 814.349ms | 4857 | 640 | 8991.24 | 939.206 | 0.0216226 | 1.09258 | 3.23286 | 0.496603 | 0.000209105 | 2.2519e-05 | 1.2868e-06 | 3(Loss) | true |
