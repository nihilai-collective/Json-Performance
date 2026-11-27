
----
### Apache Builds Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3111.35 | 0.172038 | 4885.49ms | 94653 | 320 | 797205 | 29012.5 | 0.0932255 | 1.62667 | 7.96657 | 1.55511 | 0.00490023 | 6.33894e-06 | 1.41966e-06 | 1(Win) | true |
| Glaze | 2112.6 | 0.0743122 | 6232.81ms | 94653 | 1280 | 1.29053e+06 | 42728.5 | 0.235961 | 2.41645 | 11.9558 | 2.23933 | 0.0097832 | 1.36518e-05 | 8.02273e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 2056.02 | 0.254429 | 6370.84ms | 94653 | 160 | 1.99649e+06 | 43904.2 | 0.0470278 | 2.457 | 12.2662 | 2.0331 | 0.00829801 | 1.53851e-05 | 7.06528e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1690.1 | 0.0709824 | 7335.44ms | 94653 | 1280 | 1.83973e+06 | 53409.9 | 0.0466364 | 2.99613 | 12.9941 | 2.24738 | 0.0074417 | 1.09776e-05 | 5.24944e-06 | 4(Loss) | true |
