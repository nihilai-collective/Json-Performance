
----
### Discord Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14090.4 | 0.867102 | 696.312ms | 94370 | 80 | 245387 | 6387.2 | 0.1001 | 1(Win) | true |
| Glaze | 2351.54 | 1.35527 | 3968.22ms | 94370 | 30 | 8.0711e+06 | 38272 | 0.0892658 | 2(Loss) | true |
| simdjson (reflection) | 302.742 | 0.235931 | 7138.26ms | 94370 | 80 | 3.93535e+07 | 297277 | 0.279577 | 3(Loss) | true |
