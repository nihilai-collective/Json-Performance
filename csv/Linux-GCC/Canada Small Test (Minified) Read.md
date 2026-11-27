
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 955.67 | 0.0599131 | 493.599ms | 4630 | 30 | 229.885 | 4620.33 | 0.115299 | 2.57693 | 1(Win) | true |
| Jsonifier (two-stage) | 833.399 | 0.261488 | 590.274ms | 4630 | 40 | 7677.5 | 5298.2 | 0.371311 | 2.956 | 2(Loss) | true |
| simdjson (reflection) | 714.421 | 0.0852775 | 630.933ms | 4630 | 40 | 1111.18 | 6180.55 | 0.0418153 | 3.4514 | 3(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 699.318 | 0.0877889 | 653.86ms | 4630 | 40 | 1229 | 6314.02 | 0.461511 | 3.52472 | 4(Tie) | true |
| Glaze STATISTICAL TIE | 697.344 | 0.502748 | 640.881ms | 4630 | 640 | 648558 | 6331.9 | 0.396814 | 3.53528 | 4(Tie) | true |
