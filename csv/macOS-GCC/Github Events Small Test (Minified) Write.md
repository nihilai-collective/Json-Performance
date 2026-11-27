
----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 11418.9 | 4.43328 | 20.2821ms | 1996 | 2560 | 139818 | 166.7 | 2.74212 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 10400.6 | 3.03027 | 20.779ms | 1996 | 4890 | 150410 | 183.022 | 1.00534 | 1(Tie) | true |
| Glaze | 2662.29 | 1.87718 | 70.402ms | 1996 | 1280 | 230587 | 715 | 1.27479 | 3(Loss) | true |
