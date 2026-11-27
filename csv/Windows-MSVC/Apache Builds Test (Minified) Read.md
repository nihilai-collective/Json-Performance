
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 774.461 | 0.886897 | 6041.21ms | 94653 | 640 | 6.83906e+08 | 116556 | 0.304316 | 3.19592 | 1(Win) | true |
| Glaze | 716.209 | 0.29183 | 6639.95ms | 94653 | 2560 | 3.46328e+08 | 126036 | 0.0439909 | 3.45584 | 2(Loss) | true |
| Jsonifier (two-stage) | 702.53 | 0.783336 | 6657.19ms | 94653 | 640 | 6.48357e+08 | 128490 | 0.405964 | 3.52323 | 3(Loss) | true |
| simdjson (ondemand) | 622.349 | 0.373524 | 7540.01ms | 94653 | 2560 | 7.51413e+08 | 145044 | 0.000888729 | 3.97728 | 4(Loss) | true |
