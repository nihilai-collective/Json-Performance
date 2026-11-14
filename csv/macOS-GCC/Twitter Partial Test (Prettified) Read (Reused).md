
----
### Twitter Partial Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Partial%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 5191.31 | 0.416282 | 6565.09ms | 631514 | 40 | 9.32926e+06 | 116013 | 0.2037 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 5162.26 | 0.218661 | 6211.75ms | 631514 | 160 | 1.04124e+07 | 116666 | 0.856607 | 1(Tie) | true |
| simdjson (ondemand) | 4579.37 | 0.923249 | 7676.17ms | 631514 | 30 | 4.42297e+07 | 131516 | 0.0129786 | 3(Loss) | true |
| simdjson (reflection) | 4413.13 | 0.0603674 | 7045.6ms | 631514 | 2560 | 1.73747e+07 | 136470 | 0.121787 | 4(Loss) | true |
| Glaze | 2633.28 | 1.88021 | 6077.91ms | 631514 | 30 | 5.54763e+08 | 228710 | 0.792123 | 5(Loss) | true |
