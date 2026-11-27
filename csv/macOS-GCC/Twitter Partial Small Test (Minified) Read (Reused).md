
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3973.99 | 1.36215 | 76.738ms | 2889 | 2560 | 228314 | 693.3 | 1.53779 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 3776.27 | 1.86299 | 75.8989ms | 2889 | 1280 | 236483 | 729.6 | 0.551268 | 2(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 3753.12 | 1.24039 | 81.5322ms | 2889 | 2560 | 212259 | 734.1 | 3.24895 | 2(Tie) | true |
| simdjson (reflection) | 3548.64 | 1.52122 | 80.7731ms | 2889 | 1280 | 178552 | 776.4 | 4.52342 | 4(Loss) | true |
| Glaze | 2309.36 | 0.513117 | 128.595ms | 2889 | 4890 | 183254 | 1193.04 | 0.422021 | 5(Loss) | true |
