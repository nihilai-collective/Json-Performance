
----
### Random Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1334.3 | 0.814313 | 5348.4ms | 461466 | 30 | 2.16409e+08 | 329827 | 1.28567 | 2.27758 | 1(Win) | true |
| Glaze STATISTICAL TIE | 959.807 | 0.152961 | 7240.13ms | 461466 | 40 | 1.96758e+07 | 458518 | 0.307834 | 3.16648 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 952.103 | 0.52272 | 6972.49ms | 461466 | 320 | 1.8681e+09 | 462228 | 0.679099 | 3.19172 | 2(Tie) | true |
| simdjson (ondemand) | 698.675 | 1.06569 | 9091.8ms | 461466 | 160 | 7.20957e+09 | 629890 | 0.314144 | 4.34938 | 4(Loss) | true |
