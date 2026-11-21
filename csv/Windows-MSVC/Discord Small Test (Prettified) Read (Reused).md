
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1781.65 | 0.116266 | 455.573ms | 6701 | 160 | 2782.63 | 3586.88 | 0.0870474 | 1.37845 | 1(Win) | true |
| Jsonifier (two-stage) | 1507.15 | 0.249029 | 493.234ms | 6701 | 640 | 71358.3 | 4240.16 | 0.0552445 | 1.63171 | 2(Loss) | true |
| Jsonifier STATISTICAL TIE | 1465.89 | 0.195251 | 548.51ms | 6701 | 4890 | 354302 | 4359.53 | 0.440722 | 1.67873 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1465.73 | 0.197779 | 492.749ms | 6701 | 40 | 2974.36 | 4360 | 0.0763942 | 1.6842 | 3(Tie) | true |
