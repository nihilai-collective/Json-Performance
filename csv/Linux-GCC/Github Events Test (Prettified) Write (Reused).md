
----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16839.8 | 0.0406216 | 1181.93ms | 78778 | 4890 | 16060.5 | 4461.36 | 0.275681 | 0.306426 | 0.845566 | 0.121366 | 3.60932e-05 | 1.11883e-05 | 5.58635e-06 | 1(Win) | true |
| Glaze | 5399.63 | 0.397348 | 2123.25ms | 78778 | 160 | 489039 | 13913.6 | 0.0403218 | 0.946398 | 2.80596 | 0.434093 | 6.77537e-05 | 1.56294e-05 | 8.56838e-06 | 2(Loss) | true |
| simdjson (reflection) | 644.682 | 0.473021 | 6347.19ms | 78778 | 160 | 4.86183e+07 | 116536 | 0.341103 | 7.86333 | 29.3676 | 6.60714 | 0.0357785 | 0.00758111 | 0.000164862 | 3(Loss) | true |
