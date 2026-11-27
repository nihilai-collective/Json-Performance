
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 11928.1 | 0.208902 | 5115.82ms | 631514 | 320 | 3.56008e+06 | 50490.7 | 0.0199519 | 0.207436 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 11913.2 | 0.0808614 | 5147.31ms | 631514 | 2560 | 4.27795e+06 | 50554.1 | 0.0457693 | 0.207677 | 1(Tie) | true |
| simdjson (ondemand) | 9628.26 | 0.100515 | 6483.11ms | 631514 | 640 | 2.52993e+06 | 62551.2 | 0.0228835 | 0.256996 | 3(Loss) | true |
| Glaze | 4016.15 | 0.245587 | 7772.34ms | 631514 | 40 | 5.4252e+06 | 149959 | 0.0385086 | 0.61635 | 4(Loss) | true |
